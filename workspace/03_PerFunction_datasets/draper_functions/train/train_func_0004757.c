move_to_string(int move, char string[], int size) {

   ASSERT(move==MoveNull||move_is_ok(move));
   ASSERT(string!=NULL);
   ASSERT(size>=6);

   if (size < 6) return false;


   if (move == MoveNull || move == MoveNone) {
      strcpy(string,NullMoveString);
      return true;
   }


   square_to_string(MOVE_FROM(move),&string[0],3);
   square_to_string(MOVE_TO(move),&string[2],3);
   ASSERT(strlen(string)==4);


   if (MOVE_IS_PROMOTE(move)) {
      string[4] = tolower(piece_to_char(move_promote(move)));
      string[5] = '\0';
   }

   return true;
}
