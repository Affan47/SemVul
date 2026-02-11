KeyMayMatch(const Slice& key, const Slice& bloom_filter) const {
    const size_t len = bloom_filter.size();
    if (len < 2) return false;

    const char* array = bloom_filter.data();
    const size_t bits = (len - 1) * 8;


    const size_t k = array[len-1];
    if (k > 30) {


      return true;
    }

    uint32_t h = BloomHash(key);
    const uint32_t delta = (h >> 17) | (h << 15);
    for (size_t j = 0; j < k; j++) {
      const uint32_t bitpos = h % bits;
      if ((array[bitpos/8] & (1 << (bitpos % 8))) == 0) return false;
      h += delta;
    }
    return true;
  }
