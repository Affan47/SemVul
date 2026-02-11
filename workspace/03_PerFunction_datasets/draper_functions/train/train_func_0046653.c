GetRank(int const card_one, int const card_two,
                                 int const card_three, int const card_four,
                                 int const card_five) const {
  if ((mDeckcardsSuit[card_one] == mDeckcardsSuit[card_two]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_three]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_four]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_five])) {
    return mFlushRankPtr[mDeckcardsFlush[card_one] +
                         mDeckcardsFlush[card_two] +
                         mDeckcardsFlush[card_three] +
                         mDeckcardsFlush[card_four] +
                         mDeckcardsFlush[card_five]];
  }
  return mRankPtr[mDeckcardsFace[card_one] +
                  mDeckcardsFace[card_two] +
                  mDeckcardsFace[card_three] +
                  mDeckcardsFace[card_four] +
                  mDeckcardsFace[card_five]];
}
