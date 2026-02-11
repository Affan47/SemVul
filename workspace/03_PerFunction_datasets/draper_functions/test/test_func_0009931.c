ToComplex(Spectrum &out)
	{
		Array<Complex>* outbuffer;

		outbuffer = &out.GetComplexArray();
		(*outbuffer)[0].SetReal(fftbuffer[0]);
		(*outbuffer)[0].SetImag(0);
		(*outbuffer)[mSize/2].SetReal(fftbuffer[1]);
		(*outbuffer)[mSize/2].SetImag(0);

		for (int i=1; i< mSize/2; i++) {
			(*outbuffer)[i].SetReal(fftbuffer[2*i]);
			(*outbuffer)[i].SetImag(-fftbuffer[2*i+1]);
		}

		outbuffer->SetSize(mSize/2+1);
	}
