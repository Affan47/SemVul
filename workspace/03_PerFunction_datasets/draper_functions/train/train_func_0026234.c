ZopfliGetDistSymbol(int dist) {
#if HAVE_BUILTIN_CLZ
  if (dist < 5) {
    return dist - 1;
  } else {
    int l = (31 ^ __builtin_clz(dist - 1));
    int r = ((dist - 1) >> (l - 1)) & 1;
    return l * 2 + r;
  }
#else
  if (dist < 193) {
    if (dist < 13) {
      if (dist < 5) return dist - 1;
      else if (dist < 7) return 4;
      else if (dist < 9) return 5;
      else return 6;
    } else {
      if (dist < 17) return 7;
      else if (dist < 25) return 8;
      else if (dist < 33) return 9;
      else if (dist < 49) return 10;
      else if (dist < 65) return 11;
      else if (dist < 97) return 12;
      else if (dist < 129) return 13;
      else return 14;
    }
  } else {
    if (dist < 2049) {
      if (dist < 257) return 15;
      else if (dist < 385) return 16;
      else if (dist < 513) return 17;
      else if (dist < 769) return 18;
      else if (dist < 1025) return 19;
      else if (dist < 1537) return 20;
      else return 21;
    } else {
      if (dist < 3073) return 22;
      else if (dist < 4097) return 23;
      else if (dist < 6145) return 24;
      else if (dist < 8193) return 25;
      else if (dist < 12289) return 26;
      else if (dist < 16385) return 27;
      else if (dist < 24577) return 28;
      else return 29;
    }
  }
#endif
}
