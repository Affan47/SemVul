pv_is_ok(const mv_t pv[]) {

   int pos;
   int move;

   if (pv == NULL) return false;

   for (pos = 0; true; pos++) {

      if (pos >= 256) return false;
      move = pv[pos];

      if (move == MoveNone) return true;
      if (!move_is_ok(move)) return false;
   }

   return true;
}
