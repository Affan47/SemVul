Stage3end_best_score (List_T hits) {
  List_T p;
  T hit;
  int best_score = 1000000;

  for (p = hits; p != NULL; p = p->rest) {
    hit = (T) p->first;
    if (hit->score < best_score) {
      best_score = hit->score;
    }
  }

  return best_score;
}
