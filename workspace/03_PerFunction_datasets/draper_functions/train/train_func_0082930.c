init_z(harminv_data d, int J, cmplx *z)
{
     d->J = J;
     d->z = z;
     CHK_MALLOC(d->U0, cmplx, J*J);
     CHK_MALLOC(d->U1, cmplx, J*J);
     generate_U(d->U0, d->U1, 0, d->c, d->n, d->K, d->J, d->J, d->z, d->z,
		&d->G0, &d->G0_M, &d->D0);
}
