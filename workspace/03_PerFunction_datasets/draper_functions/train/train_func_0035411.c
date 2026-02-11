as_vector()
{
 std::vector<item> ret;
 for (int i = 0; i < size(); i++) {
  for (int j = 0; j < stack_at(i).size(); j++)
   ret.push_back(items[i][j]);
 }
 return ret;
}
