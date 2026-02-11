sanei_hp_accessor_choice_strlist (HpAccessorChoice this,
			    HpOptSet optset, HpData data,
                            const HpDeviceInfo *info)
{
  if (optset)
    {
      int	old_val = hp_accessor_choice_getint((HpAccessor)this, data);
      HpChoice	choice;
      size_t	count	= 0;

      for (choice = this->choices; choice; choice = choice->next)
	  if (sanei_hp_choice_isEnabled(choice, optset, data, info))
	      this->strlist[count++] = choice->name;
      this->strlist[count] = 0;

      hp_accessor_choice_setint((HpAccessor)this, data, old_val);
    }

  return this->strlist;
}
