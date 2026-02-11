remove_mutation(game *g, pl_flag mut)
{

 pl_flag replacing = PF_NULL;
 std::vector<pl_flag> originals = g->mutation_data[mut].prereqs;
 for (int i = 0; replacing == PF_NULL && i < originals.size(); i++) {
  pl_flag pre = originals[i];
  for (int j = 0; replacing == PF_NULL &&
                  j < g->mutation_data[pre].replacements.size(); j++) {
   if (g->mutation_data[pre].replacements[j] == mut)
    replacing = pre;
  }
 }

 toggle_trait(mut);
 if (replacing != PF_NULL) {
  g->add_msg("Your %s turns into %s.", traits[mut].name.c_str(),
             traits[replacing].name.c_str());
  toggle_trait(replacing);
  mutation_effect(g, *this, replacing);
 } else
  g->add_msg("You lose your %s.", traits[mut].name.c_str());

}
