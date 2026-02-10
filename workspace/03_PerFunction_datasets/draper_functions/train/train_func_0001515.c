pop_new_stack_if_no_contents (XlwMenuWidget mw)
{
  if (mw->menu.new_depth > 1)
    {
      if (!mw->menu.new_stack [mw->menu.new_depth - 1]->contents)
	mw->menu.new_depth -= 1;
    }
}
