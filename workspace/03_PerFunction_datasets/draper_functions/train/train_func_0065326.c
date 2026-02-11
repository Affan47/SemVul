SR_Get_Module_3(WamWord desc_word, WamWord module_name_word,
		WamWord interface_word)
{
  SRInf *sr = Get_Descriptor(desc_word, FALSE);
  SRModule *m = sr->cur_module;

  Check_For_Un_Atom(module_name_word);
  Check_For_Un_Atom(interface_word);

  if (m == NULL)
    return FALSE;

  if (!Get_Atom(m->atom_module_name, module_name_word))
    return FALSE;

  if (sr->interface)
    return Un_String("interface", interface_word);

  return Un_String("body", interface_word);
}
