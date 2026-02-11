get_column_to_expand(guint& column_to_expand) const
{

  column_to_expand = 0;
  bool result = false;


  guint i = 0;
  for(type_column_items::const_iterator iter = m_column_items.begin(); iter != m_column_items.end(); ++iter)
  {
    sharedptr<LayoutItem> layout_item = *iter;

    sharedptr<LayoutItem_Field> layout_item_field = sharedptr<LayoutItem_Field>::cast_dynamic(layout_item);
    if(layout_item_field)
    {


      if(layout_item_field->get_glom_type() == Field::TYPE_TEXT)
      {

        const guint column_width = layout_item_field->get_display_width();
        if(!column_width)
        {
          column_to_expand = i;
          result = true;
        }

      }
    }

    ++i;
  }

  return result;
}
