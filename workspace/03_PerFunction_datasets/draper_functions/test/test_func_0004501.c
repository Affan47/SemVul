answer_log(lListElem *answer, bool show_info) {

   bool ret = false;

   DENTER(ANSWER_LAYER, "answer_log");

   if (!answer) {
      DRETURN(ret);
   }

   switch (lGetUlong(answer, AN_quality)) {
      case ANSWER_QUALITY_CRITICAL:
         CRITICAL((SGE_EVENT, lGetString(answer, AN_text)));
         ret = true;
         break;
      case ANSWER_QUALITY_ERROR:
         ERROR((SGE_EVENT, lGetString(answer, AN_text)));
         ret = true;
         break;
      case ANSWER_QUALITY_WARNING:
         WARNING((SGE_EVENT, lGetString(answer, AN_text)));
         break;
      case ANSWER_QUALITY_INFO:
         if (show_info) {
            INFO((SGE_EVENT, lGetString(answer, AN_text)));
         }
         break;
      default:
         break;
   }

   DRETURN(ret);
}
