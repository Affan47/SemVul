GetAllEffects(int type) const {
   EffectSet result = GetEffects(type);
   CategorySet::const_iterator iter;
   for (iter = mSubCategories.begin(); iter != mSubCategories.end(); ++iter) {
      EffectSet tmp = (*iter)->GetAllEffects(type);
      EffectSet::const_iterator itr2;
      for (itr2 = tmp.begin(); itr2 != tmp.end(); ++itr2)
         result.insert(*itr2);
   }
   return result;
}
