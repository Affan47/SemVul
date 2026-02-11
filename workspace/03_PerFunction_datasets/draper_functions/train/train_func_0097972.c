v5dWriteCompressedGrid(const v5dstruct * v, int time, int var,
			   const float *ga, const float *gb,
			   const void *compdata)
{
    int pos, n, k;


    if (v->Mode != 'w') {
	printf("Error in v5dWriteCompressedGrid: file opened for reading,");
	printf(" not writing.\n");
	return 0;
    }
    if (time < 0 || time >= v->NumTimes) {
	printf
	    ("Error in v5dWriteCompressedGrid: bad timestep argument (%d)\n",
	     time);
	return 0;
    }
    if (var < 0 || var >= v->NumVars) {
	printf
	    ("Error in v5dWriteCompressedGrid: bad variable argument (%d)\n",
	     var);
	return 0;
    }


    pos = grid_position(v, time, var);
    if (lseek(v->FileDesc, pos, SEEK_SET) < 0) {

	printf
	    ("Error in v5dWrite[Compressed]Grid: seek failed, disk full?\n");
	return 0;
    }


    k = 0;
    if (write_float4_array(v->FileDesc, ga, v->Nl[var]) == v->Nl[var] &&
	write_float4_array(v->FileDesc, gb, v->Nl[var]) == v->Nl[var]) {

	n = v->Nr * v->Nc * v->Nl[var];
	if (v->CompressMode == 1) {
	    k = write_block(v->FileDesc, compdata, n, 1) == n;
	}
	else if (v->CompressMode == 2) {
	    k = write_block(v->FileDesc, compdata, n, 2) == n;
	}
	else if (v->CompressMode == 4) {
	    k = write_block(v->FileDesc, compdata, n, 4) == n;
	}
    }

    if (k == 0) {

	printf
	    ("Error in v5dWrite[Compressed]Grid: write failed, disk full?\n");
    }
    return k;


}
