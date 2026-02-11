difilt(PLINT *myxscl, PLINT *myyscl, PLINT npts,
       PLINT *clpxmi, PLINT *clpxma, PLINT *clpymi, PLINT *clpyma)
{
    PLINT i, x, y;


    if (plsc->difilt & PLDI_MAP) {
	for (i = 0; i < npts; i++) {
	    myxscl[i] = plsc->dimxax * myxscl[i] + plsc->dimxb;
	    myyscl[i] = plsc->dimyay * myyscl[i] + plsc->dimyb;
	}
    }


    if (plsc->difilt & PLDI_ORI) {
	for (i = 0; i < npts; i++) {
	    x = plsc->dioxax * myxscl[i] + plsc->dioxay * myyscl[i] +
		plsc->dioxb;
	    y = plsc->dioyax * myxscl[i] + plsc->dioyay * myyscl[i] +
		plsc->dioyb;
	    myxscl[i] = x;
	    myyscl[i] = y;
	}
    }


    if (plsc->difilt & PLDI_PLT) {
	for (i = 0; i < npts; i++) {
	    myxscl[i] = plsc->dipxax * myxscl[i] + plsc->dipxb;
	    myyscl[i] = plsc->dipyay * myyscl[i] + plsc->dipyb;
	}
    }


    if (plsc->difilt & PLDI_DEV) {
	for (i = 0; i < npts; i++) {
	    myxscl[i] = plsc->didxax * myxscl[i] + plsc->didxb;
	    myyscl[i] = plsc->didyay * myyscl[i] + plsc->didyb;
	}
	*clpxmi = plsc->diclpxmi;
	*clpxma = plsc->diclpxma;
	*clpymi = plsc->diclpymi;
	*clpyma = plsc->diclpyma;
    }
    else {
      *clpxmi = plsc->phyxmi;
      *clpxma = plsc->phyxma;
      *clpymi = plsc->phyymi;
      *clpyma = plsc->phyyma;
    }
}
