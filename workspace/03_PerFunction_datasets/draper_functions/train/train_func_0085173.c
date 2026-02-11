Substring_compare (T substring1, T substring2) {
  if (substring1 == NULL && substring2 == NULL) {
    return 0;
  } else if (substring1 == NULL) {
    return -1;
  } else if (substring2 == NULL) {
    return +1;
  } else if (substring1->alignstart < substring2->alignstart) {
    return -1;
  } else if (substring1->alignstart > substring2->alignstart) {
    return +1;
  } else if (substring1->alignend < substring2->alignend) {
    return -1;
  } else if (substring1->alignend > substring2->alignend) {
    return +1;
  } else {
    return 0;
  }
}
