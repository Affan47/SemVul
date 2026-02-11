appendGame(ChessGame *cg,bool RenumberDupes) {
  if (RenumberDupes) clearDupes(cg);
  GameList.push_back(cg);
}
