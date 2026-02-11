load (CTree &tree, bool start)
{
  LNodeAS::iterator  endNodeAS, itNodeAS;


  endNodeAS = tree.nodes.end ();
  for (itNodeAS = tree.nodes.begin (); itNodeAS != endNodeAS; itNodeAS++) {
    if (!start && ((*itNodeAS)->point.z() == 0)) continue;

    push (*itNodeAS);
  }
}
