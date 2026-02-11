visit (Ekiga::FormVisitor &visitor) const
{
  std::list<struct HiddenField>::const_iterator iter_hidden = hiddens.begin ();
  std::list<struct BooleanField>::const_iterator iter_bool = booleans.begin ();
  std::list<struct TextField>::const_iterator iter_text = texts.begin ();
  std::list<struct TextField>::const_iterator iter_private_text = private_texts.begin ();
  std::list<struct MultiTextField>::const_iterator iter_multi_text = multi_texts.begin ();
  std::list<struct SingleChoiceField>::const_iterator iter_single_choice = single_choices.begin ();
  std::list<struct MultipleChoiceField>::const_iterator iter_multiple_choice = multiple_choices.begin ();
  std::list<struct EditableSetField>::const_iterator iter_editable_set = editable_sets.begin ();

  visitor.title (my_title);
  visitor.instructions (my_instructions);
  if (!my_link.first.empty () && !my_link.second.empty ())
    visitor.link (my_link.first, my_link.second);
  visitor.error (my_error);

  for (std::list<FieldType>::const_iterator iter = ordering.begin ();
       iter != ordering.end ();
       iter++) {

    switch (*iter) {

    case HIDDEN:

      visitor.hidden (iter_hidden->name, iter_hidden->value);
      iter_hidden++;
      break;

    case BOOLEAN:

      visitor.boolean (iter_bool->name,
		       iter_bool->description,
		       iter_bool->value,
		       iter_bool->advanced);
      iter_bool++;
      break;

    case TEXT:

      visitor.text (iter_text->name, iter_text->description,
               iter_text->value, iter_text->tooltip, iter_text->advanced);
      iter_text++;
      break;

    case PRIVATE_TEXT:

      visitor.private_text (iter_private_text->name,
			    iter_private_text->description,
			    iter_private_text->value,
			    iter_private_text->tooltip,
			    iter_private_text->advanced);
      iter_private_text++;
      break;

    case MULTI_TEXT:

      visitor.multi_text (iter_multi_text->name,
			  iter_multi_text->description,
			  iter_multi_text->value,
			  iter_multi_text->advanced);
      iter_multi_text++;
      break;

    case SINGLE_CHOICE:

      visitor.single_choice (iter_single_choice->name,
			     iter_single_choice->description,
			     iter_single_choice->value,
			     iter_single_choice->choices,
			     iter_single_choice->advanced);
      iter_single_choice++;
      break;

    case MULTIPLE_CHOICE:

      visitor.multiple_choice (iter_multiple_choice->name,
			       iter_multiple_choice->description,
			       iter_multiple_choice->values,
			       iter_multiple_choice->choices,
			       iter_multiple_choice->advanced);
      iter_multiple_choice++;
      break;

    case EDITABLE_SET:

      visitor.editable_set (iter_editable_set->name,
			    iter_editable_set->description,
			    iter_editable_set->values,
			    iter_editable_set->proposed_values,
			    iter_editable_set->advanced);
      iter_editable_set++;
      break;

    default:
      break;
    }
  }
}
