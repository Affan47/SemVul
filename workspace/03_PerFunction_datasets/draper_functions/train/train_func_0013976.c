select(double number) const {

   if ( ruleHeader != NULL ) {
       if (ruleHeader->isFulfilled(number)) {
           return keyword;
       }
   }
   if ( next != NULL ) {
       return next->select(number);
   }
   else {
       return UnicodeString(TRUE, PLURAL_KEYWORD_OTHER, 5);
   }

}
