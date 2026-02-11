updateStock() {
  if (over)
    return;
  if (!myboard)
    return;
  if (!moves.empty())
    myboard->setInfo(5,moves.back().getHouseString());


  if (protodata[2])
    global.bugpane->setPosition(moves.back());
}
