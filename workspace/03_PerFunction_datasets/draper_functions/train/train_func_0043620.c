do_test_init_to_unit(size_t N)
{
	CMatrixDouble	 dense1;
	dense1.unit(N,1.0);

	CSparseMatrix SM(dense1);

	CMatrixDouble    dense_out;
	SM.get_dense(dense_out);

	EXPECT_TRUE( dense_out==dense1 ) <<
		"Failed with N=" << N << "\n";
}
