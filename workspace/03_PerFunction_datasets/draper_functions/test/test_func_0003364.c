ExportImage (ml_state_t *msp, int kind, FILE *file)
{
    heap_t	*heap = msp->ml_heap;


    status_t	status = SUCCESS;
    export_table_t *exportTbl;
    writer_t	*wr;

#define SAVE_REG(dst, src)	{				\
	    ml_val_t	__src = (src);				\
	    if (isEXTERN(BIBOP, __src))				\
		__src = ExportCSymbol(exportTbl, __src);	\
	    (dst) = __src;					\
	}

    if ((wr = WR_OpenFile(file)) == NIL(writer_t *))
	return FAILURE;


    InvokeGC (msp, 0);
    InvokeGC (msp, MAX_NGENS);

    exportTbl = ScanHeap(heap);

    {
	ml_heap_hdr_t	heapHdr;

	heapHdr.numVProcs	= 1;
	heapHdr.numGens		= heap->numGens;
	heapHdr.numArenas	= NUM_ARENAS;
	heapHdr.numBOKinds	= NUM_BIGOBJ_KINDS;
	heapHdr.numBORegions	= heap->numBORegions;
	heapHdr.cacheGen	= heap->cacheGen;
	heapHdr.allocSzB	= heap->allocSzB / MAX_NUM_PROCS;

	SAVE_REG(heapHdr.pervStruct, *PTR_MLtoC(ml_val_t, PervStruct));
	SAVE_REG(heapHdr.runTimeCompUnit, RunTimeCompUnit);
#ifdef ASM_MATH
	SAVE_REG(heapHdr.mathVec, MathVec);
#else
	heapHdr.mathVec = ML_unit;
#endif

	HeapIO_WriteImageHeader(wr, kind);
	WR_Write(wr, &heapHdr, sizeof(heapHdr));
	if (WR_Error(wr)) {
	    WR_Free(wr);
	    return FAILURE;
	}
    }


    {
	ml_vproc_image_t	image;


	SAVE_REG(image.sigHandler, DEREF(MLSignalHandler));
	SAVE_REG(image.stdArg, msp->ml_arg);
	SAVE_REG(image.stdCont, msp->ml_cont);
	SAVE_REG(image.stdClos, msp->ml_closure);
	SAVE_REG(image.pc, msp->ml_pc);
	SAVE_REG(image.exnCont, msp->ml_exnCont);
	SAVE_REG(image.varReg, msp->ml_varReg);
	SAVE_REG(image.calleeSave[0], msp->ml_calleeSave[0]);
	SAVE_REG(image.calleeSave[1], msp->ml_calleeSave[1]);
	SAVE_REG(image.calleeSave[2], msp->ml_calleeSave[2]);

	if (HeapIO_WriteExterns(wr, exportTbl) == FAILURE) {
	    status = FAILURE;
	    goto done;
	}

	WR_Write(wr, &image, sizeof(image));
	if (WR_Error(wr)) {
	    status = FAILURE;
	    goto done;
	}
    }


    if (WriteHeap(wr, heap) == FAILURE)
	status = FAILURE;

  done:;
    if (kind != EXPORT_FN_IMAGE)
	RepairHeap (exportTbl, heap);

    WR_Free(wr);

    return status;

}
