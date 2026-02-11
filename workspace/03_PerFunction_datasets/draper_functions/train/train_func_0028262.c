TestPickNextSample(int n) {
  tcmalloc::Sampler sampler;
  sampler.Init(1);
  scoped_array<uint64_t> int_random_sample(new uint64_t[n]);
  int sample_period = sampler.GetSamplePeriod();
  int ones_count = 0;
  for (int i = 0; i < n; i++) {
    int_random_sample[i] = sampler.PickNextSamplingPoint();
    CHECK_GE(int_random_sample[i], 1);
    if (int_random_sample[i] == 1) {
      ones_count += 1;
    }
    CHECK_LT(ones_count, 4);
  }

  sort(int_random_sample.get(), int_random_sample.get() + n);
  scoped_array<double> random_sample(new double[n]);


  for (int i = 0; i < n; i++) {
    random_sample[i] = 1 - exp(-static_cast<double>(int_random_sample[i])
                           / sample_period);
  }

  double geom_ad_pvalue = AndersonDarlingTest(n, random_sample.get());
  LOG(INFO) << StringPrintf("pvalue for geometric AndersonDarlingTest "
                             "with n= %d is p= %f\n", n, geom_ad_pvalue);
  CHECK_GT(min(geom_ad_pvalue, 1 - geom_ad_pvalue), 0.0001);


}
