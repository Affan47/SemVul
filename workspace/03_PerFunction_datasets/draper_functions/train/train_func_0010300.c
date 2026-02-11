Transmittance(Real* transmittance)
{
    Complex eta0, eta1;
    for (int i=0; i<N; i++)
    {
	eta0 = Complex(eta_re[incidence_medium_index][i],
		       eta_im[incidence_medium_index][i]);
	eta1 = Complex(eta_re[exit_medium_index][i],
		       eta_im[exit_medium_index][i]);
	transmittance[i] = 4.0*real(eta0)*real(eta1) / norm(eta0*B[i] + C[i]);
    }
}
