ooQ931GetIE (const Q931Message* q931msg,
                                              int ieCode)
{
   DListNode* curNode;
   unsigned int i;

   for(i = 0, curNode = q931msg->ies.head; i < q931msg->ies.count; i++) {
      Q931InformationElement *ie = (Q931InformationElement*) curNode->data;
      if (ie->discriminator == ieCode) {
         return ie;
      }
      curNode = curNode->next;
   }
   return NULL;
}
