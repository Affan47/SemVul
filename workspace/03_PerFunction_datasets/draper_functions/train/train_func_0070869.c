benchmark_mm()
{
  static const int SZ = 2000;
  static const double ALPHA=1.0, BETA=0.0;
  struct tms t1, t2;
  times(&t1);
  std::vector<double> a(SZ*SZ);
  std::vector<double> b(SZ*SZ);
  std::vector<double> c(SZ*SZ);
  for(int i=SZ*SZ-1; i>=0; i--) { a[i] = 2-i; b[i] = i;}
  mat::gemm("N","N", &SZ, &SZ, &SZ, &ALPHA, &a[0], &SZ,
            &b[0], &SZ, &BETA, &c[0], &SZ);
  times(&t2);
  printf("MM time: %6.3f s\nReference values:\nPhenom 2.4GHz/GOTO: 1.9s\n"
         "Phenom 2.4GHz/generic: 23.6s\n",
         double(t2.tms_utime-t1.tms_utime)/sysconf(_SC_CLK_TCK));
}
