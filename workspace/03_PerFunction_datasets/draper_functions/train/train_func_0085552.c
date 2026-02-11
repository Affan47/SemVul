Clock_Holiday (int month, int day, int monthStartDOW,
                           char answer[100])
{
   switch (month) {
      case 1:
         if (day == 1) {
            strcpy (answer, "New Years Day");
            return;
         } else if (ThirdMonday (monthStartDOW) == day) {
            strcpy (answer, "Martin Luther King Jr Day");
            return;
         }
         break;
      case 2:
         if (ThirdMonday (monthStartDOW) == day) {
            strcpy (answer, "Presidents Day");
            return;
         }
         break;
      case 5:
         if (Memorialday (monthStartDOW) == day) {
            strcpy (answer, "Memorial Day");
            return;
         }
         break;
      case 7:
         if (day == 4) {
            strcpy (answer, "Independence Day");
            return;
         }
         break;
      case 9:
         if (Laborday (monthStartDOW) == day) {
            strcpy (answer, "Labor Day");
            return;
         }
         break;
      case 10:
         if (Columbusday (monthStartDOW) == day) {
            strcpy (answer, "Columbus Day");
            return;
         }
         break;
      case 11:
         if (day == 11) {
            strcpy (answer, "Veterans Day");
            return;
         } else if (Thanksgivingday (monthStartDOW) == day) {
            strcpy (answer, "Thanksgiving Day");
            return;
         }
         break;
      case 12:
         if (day == 25) {
            strcpy (answer, "Christmas Day");
            return;
         }
         break;
   }
   strcpy (answer, "");
   return;
}
