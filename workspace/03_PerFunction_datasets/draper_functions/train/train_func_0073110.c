UpdateTransferMatrix(int i)
{
    int j, k;
    Real delta, helper;
    Complex eta, cdelta, A11, A12, A21, chelper;
    const Complex iu(Real(0), Real(1));

    k = material_index[i];
    if (layers[i].complex_A)
    {
	for (j=0; j<N; j++)
	{
	    cdelta = layers[i].d *
		Complex(phase_factor_re[k][j], phase_factor_im[k][j]);
	    A11 = cos(cdelta);
	    chelper = sin(cdelta);
	    eta = Complex(eta_re[k][j], eta_im[k][j]);
	    A12 = iu * chelper / eta;
	    A21 = iu * chelper * eta;
	    layers[i].a11_re[j] = real(A11);
	    layers[i].a11_im[j] = imag(A11);
	    layers[i].a12_re[j] = real(A12);
	    layers[i].a12_im[j] = imag(A12);
	    layers[i].a21_re[j] = real(A21);
	    layers[i].a21_im[j] = imag(A21);
	}
    }
    else
    {
	for (j=0; j<N; j++)
	{
	    delta = layers[i].d * phase_factor_re[k][j];
	    layers[i].a11_re[j] = cos(delta);
	    layers[i].a11_im[j] = 0.0;
	    helper = sin(delta);
	    layers[i].a12_re[j] = 0.0;
	    layers[i].a12_im[j] = helper / eta_re[k][j];
	    layers[i].a21_re[j] = 0.0;
	    layers[i].a21_im[j] = helper * eta_re[k][j];
	}
    }
}
