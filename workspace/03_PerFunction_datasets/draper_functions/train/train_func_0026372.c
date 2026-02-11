_dxf_gi_read_file(void **XF,FILE **fp)
{
  int size,s,nitems,i,f;


  if(!(_dxf_gi_importDatafile(XF,fp)))
    goto error;


  if ( _dxd_gi_majority == COL ) {
    for (s=i=0 ; i<_dxd_gi_series ; i++, s+=_dxd_gi_numflds) {
	for (f=0 ; f<_dxd_gi_numflds ; f++) {
	    size = _dxfnumGridPoints(f);
	    if (XF[s+f]) {
                XF[s+f] = reorderData(XF[s+f],f);
		if (!XF[s+f])
            		goto error;
	    }
	}
    }
  }


  if ((_dxd_gi_format == BINARY) &&
      (_dxfLocalByteOrder() != _dxd_gi_byteorder)) {
	for (f=0 ; f<_dxd_gi_numflds ; f++) {
	    if (_dxd_gi_whichflds[f]  == ON) {
	        size = _dxfnumGridPoints(f);
	        nitems = size * _dxd_gi_var[f]->datadim;
	        for (s=i=0 ; i<_dxd_gi_series ; i++, s+=_dxd_gi_numflds)
		    if ((_dxd_gi_whichser[i] == ON)  &&
	            	!_dxfByteSwap(XF[s+f], XF[s+f],
				nitems, _dxd_gi_var[f]->datatype))
			goto error;
	    }
	}
  }

#if !defined(DXD_STANDARD_IEEE)


   _dxfdenormalize(XF);
#endif


    if ((_dxd_gi_positions == FIELD_PRODUCT) &&
	(_dxd_gi_var[_dxd_gi_loc_index]->datatype != TYPE_FLOAT)) {
	int nfloats=0;
	Type ltype;
        size = _dxfnumGridPoints(_dxd_gi_loc_index);
	nfloats = _dxd_gi_var[_dxd_gi_loc_index]->datadim * size;
	ltype = _dxd_gi_var[_dxd_gi_loc_index]->datatype;
	for (s=0 ; s<_dxd_gi_series ; s++) {
	    if (_dxd_gi_whichser[s] == ON) {
		Pointer new_XF;
	        i = s*_dxd_gi_numflds + _dxd_gi_loc_index;
		new_XF = locations2float( XF[i], ltype, nfloats);
		if (!new_XF) goto error;
		DXFree(XF[i]);
		XF[i] = new_XF;
       	    }
	}
	_dxd_gi_var[_dxd_gi_loc_index]->datatype = TYPE_FLOAT;
	_dxd_gi_var[_dxd_gi_loc_index]->databytes = DXTypeSize(TYPE_FLOAT);
   }

   return OK;

error:
  return ERROR;
}
