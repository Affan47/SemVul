square_is_ok(int square) {

   if (square < 0 || square >= SquareNb) return false;

   if (SquareTo64[square] < 0) return false;

   return true;
}
