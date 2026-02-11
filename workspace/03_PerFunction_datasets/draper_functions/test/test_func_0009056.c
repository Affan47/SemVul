WriteStringInMap(const char *String) {
   void const * const oldMap = Map.Data();
   map_ptrloc const index = Map.WriteString(String);
   if (index != 0)
      ReMap(oldMap, Map.Data());
   return index;
}
