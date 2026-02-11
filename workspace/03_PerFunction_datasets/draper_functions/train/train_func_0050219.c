eval(float* result, int firstchan, int nchannels,
		      int faceid, float u, float v,
		      float , float , float , float ,
		      float , float )
    {
	if (!_tx || nchannels <= 0) return;
	if (faceid < 0 || faceid >= _tx->numFaces()) return;
	const FaceInfo& f = _tx->getFaceInfo(faceid);
	int resu = f.res.u(), resv = f.res.v();
	int ui = PtexUtils::clamp(int(u*resu), 0, resu-1);
	int vi = PtexUtils::clamp(int(v*resv), 0, resv-1);
	_tx->getPixel(faceid, ui, vi, result, firstchan, nchannels);
    }
