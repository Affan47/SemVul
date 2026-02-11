ShouldRestoreSortedPalette(int score_new, int score_orig) {
  if ((score_orig > 200) && (score_new + 100 > score_orig)) {
    return 1;
  }

  if ((score_new + 100) > (score_orig + 100) * 80 / 100) {
    return 1;
  }
  if (score_orig > 500) {

    if (score_new > 300) return 1;
  }
  return 0;
}
