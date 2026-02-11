describe()
{
 std::string ret = name + " have the ultimate goal of " +
                   facgoal_data[goal].name + ". Their primary concern is " +
                   facjob_data[job1].name;
 if (job2 == FACJOB_NULL)
  ret += ".";
 else
  ret += ", but they are also involved in " + facjob_data[job2].name + ".";
 if (values != 0) {
  ret += " They are known for ";
  for (int i = 0; i < NUM_FACVALS; i++) {
   if (has_value(faction_value(i)))
    ret += facval_data[i].name + ", ";
  }
 }
 size_t pos = ret.find_last_of(",");
 if (pos != std::string::npos) {
  ret.replace(pos, 2, ".");
  pos = ret.find_last_of(",");
  if (pos != std::string::npos)
   ret.replace(pos, 2, ", and ");
 }
 return ret;
}
