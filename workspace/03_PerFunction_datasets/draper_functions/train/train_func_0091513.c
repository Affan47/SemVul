GetFullLabel(int index) const
{

   if (index < 0 || index >= (int) mNodes.GetCount())
   {
      wxASSERT(false);
      return wxEmptyString;
   }


   KeyNode & node = mNodes[index];
   wxString label = node.label;


   if (!node.prefix.IsEmpty())
   {
      label = node.prefix + wxT(" - ") + label;
   }

   return label;
}
