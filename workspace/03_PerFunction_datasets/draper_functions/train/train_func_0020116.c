ComputeBucketCount() {

  std::vector<uint32_t> uniques(Data.size());
  for (size_t i = 0, e = Data.size(); i < e; ++i)
    uniques[i] = Data[i]->HashValue;
  array_pod_sort(uniques.begin(), uniques.end());
  std::vector<uint32_t>::iterator p =
      std::unique(uniques.begin(), uniques.end());
  uint32_t num = std::distance(uniques.begin(), p);


  if (num > 1024)
    Header.bucket_count = num / 4;
  else if (num > 16)
    Header.bucket_count = num / 2;
  else
    Header.bucket_count = num > 0 ? num : 1;

  Header.hashes_count = num;
}
