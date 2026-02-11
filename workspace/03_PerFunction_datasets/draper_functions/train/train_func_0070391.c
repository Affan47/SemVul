visit_children(Dwarf_die* parent, Dwarf_die* context)
{
  off_t next_offset = 0;
  for (off_t die_offset = parent->child_offset();
       die_offset != 0;
       die_offset = next_offset)
    {
      Dwarf_die die(this, die_offset, parent);
      if (die.tag() == 0)
	break;
      this->visit_die(&die, context);
      next_offset = die.sibling_offset();
    }
}
