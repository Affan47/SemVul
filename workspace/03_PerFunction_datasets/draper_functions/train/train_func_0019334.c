SetType(PartType t) {
   if (GetDescription() == partitionType.UTypeName()) {
      SetName(t.TypeName());
   }
   partitionType = t;
}
