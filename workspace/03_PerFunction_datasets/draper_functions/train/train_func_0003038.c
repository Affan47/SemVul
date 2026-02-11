GetRank(int const card_one, int const card_two,
                                 int const card_three, int const card_four,
                                 int const card_five, int const card_six,
                                 int const card_seven) const {
  int const seven_cards[7] = {card_one, card_two, card_three, card_four,
    card_five, card_six, card_seven};
  int temp[5];

  short unsigned best_rank_so_far = 0, current_rank = 0;
  int m = 0;

  for (int i = 1; i < 7; ++i) {
    for (int j = 0; j < i; ++j) {
      m = 0;
      for (int k = 0; k < 7; ++k) {
        if (k != i && k !=j) {
          temp[m++] = seven_cards[k];
        }
      }
      current_rank = GetRank(temp[0], temp[1], temp[2], temp[3], temp[4]);
      if (best_rank_so_far < current_rank) {
        best_rank_so_far = current_rank;
      }
    }
  }
  return best_rank_so_far;
}
