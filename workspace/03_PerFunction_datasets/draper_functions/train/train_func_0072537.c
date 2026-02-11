qmonRequestEditResource(Widget w, XtPointer cld, XtPointer cad)
{
   XmIconListCallbackStruct *cbs = (XmIconListCallbackStruct*) cad;
   long how = (long)cld;
   lList *rll;
   int type;
   char stringval[CL_MAXHOSTLEN];
   int status = 0;
   StringConst strval;
   lListElem *ep = NULL;


   DENTER(GUI_LAYER, "qmonRequestEditResource");

   rll = qmonGetResources(qmonMirrorList(SGE_CE_LIST),
                                       REQUESTABLE_RESOURCES);

   if (!how) {
      fill_in_request = lGetElemStr(rll, CE_name, cbs->element->string[0]);
   } else {
      if (!hard_soft) {
         fill_in_request = lGetElemStr(hard_requests, CE_name,
                                          cbs->element->string[0]);
      } else {
         fill_in_request = lGetElemStr(soft_requests, CE_name,
                                          cbs->element->string[0]);
      }
   }


   if (!fill_in_request) {
      goto error_exit;
   }


   type = lGetUlong(fill_in_request, CE_valtype);
   strval = lGetString(fill_in_request, CE_stringval);
   sge_strlcpy(stringval, strval, CL_MAXHOSTLEN);

   status = qmonRequestInput(w, type, cbs->element->string[0],
                              stringval, sizeof(stringval));


   if (status) {
      lSetString(fill_in_request, CE_stringval, stringval);
      lSetString(fill_in_request, CE_default, NULL);


      if (!how) {
         if (hard_soft) {
            if (!soft_requests) {
               soft_requests = lCreateList("soft_requests", CE_Type);
            }
            if (!(ep = lGetElemStr(soft_requests, CE_name,
                                    cbs->element->string[0]))) {
               lAppendElem(soft_requests, lCopyElem(fill_in_request));
            } else {
               lSetString(ep, CE_stringval, lGetString(fill_in_request, CE_stringval));
               lSetString(ep, CE_default, NULL);
            }

         } else {
            if (!hard_requests) {
               hard_requests = lCreateList("hard_requests", CE_Type);
            }
            if (!(ep = lGetElemStr(hard_requests, CE_name,
                                    cbs->element->string[0]))) {
               lAppendElem(hard_requests, lCopyElem(fill_in_request));
            } else {
               lSetString(ep, CE_stringval, lGetString(fill_in_request, CE_stringval));
               lSetString(ep, CE_default, NULL);
            }
         }
      }
      qmonRequestDraw(request_sr, soft_requests, 1);
      qmonRequestDraw(request_hr, hard_requests, 1);
   }

error_exit:
   lFreeList(&rll);
   DEXIT;
}
