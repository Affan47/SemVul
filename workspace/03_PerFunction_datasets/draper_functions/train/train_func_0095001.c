find_liberties_and_neighbors(int s)
{
  int pos;
  int other = OTHER_COLOR(string[s].color);


  liberty_mark++;
  string_mark++;


  pos = FIRST_STONE(s);
  do {


    if (UNMARKED_LIBERTY(SOUTH(pos))) {
      ADD_AND_MARK_LIBERTY(s, SOUTH(pos));
    }
    else if (UNMARKED_COLOR_STRING(SOUTH(pos), other)) {
      ADD_NEIGHBOR(s, SOUTH(pos));
      MARK_STRING(SOUTH(pos));
    }

    if (UNMARKED_LIBERTY(WEST(pos))) {
      ADD_AND_MARK_LIBERTY(s, WEST(pos));
    }
    else if (UNMARKED_COLOR_STRING(WEST(pos), other)) {
      ADD_NEIGHBOR(s, WEST(pos));
      MARK_STRING(WEST(pos));
    }

    if (UNMARKED_LIBERTY(NORTH(pos))) {
      ADD_AND_MARK_LIBERTY(s, NORTH(pos));
    }
    else if (UNMARKED_COLOR_STRING(NORTH(pos), other)) {
      ADD_NEIGHBOR(s, NORTH(pos));
      MARK_STRING(NORTH(pos));
    }

    if (UNMARKED_LIBERTY(EAST(pos))) {
      ADD_AND_MARK_LIBERTY(s, EAST(pos));
    }
    else if (UNMARKED_COLOR_STRING(EAST(pos), other)) {
      ADD_NEIGHBOR(s, EAST(pos));
      MARK_STRING(EAST(pos));
    }

    pos = NEXT_STONE(pos);
  } while (!BACK_TO_FIRST_STONE(s, pos));
}
