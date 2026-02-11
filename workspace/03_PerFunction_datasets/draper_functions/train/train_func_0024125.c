ShowBody(struct Body *body,int indent)

{ struct Rlist *rp;
  struct Constraint *cp;

fprintf(FREPORT_TXT,"%s body for type %s",body->name,body->type);
fprintf(FREPORT_HTML," %s%s%s ",CFH[cfx_blocktype][cfb],body->type,CFH[cfx_blocktype][cfe]);

fprintf(FREPORT_HTML,"%s%s%s",CFH[cfx_blockid][cfb],body->name,CFH[cfx_blockid][cfe]);

if (body->args == NULL)
   {
   fprintf(FREPORT_HTML,"%s(no parameters)%s\n",CFH[cfx_args][cfb],CFH[cfx_args][cfe]);
   fprintf(FREPORT_TXT,"(no parameters)\n");
   }
else
   {
   fprintf(FREPORT_HTML,"(");
   fprintf(FREPORT_TXT,"\n");

   for (rp = body->args; rp != NULL; rp=rp->next)
      {
      if (rp->type != CF_SCALAR)
         {
         FatalError("ShowBody - non-scalar parameter container");
         }

      fprintf(FREPORT_HTML,"%s%s%s,\n",CFH[cfx_args][cfb],(char *)rp->item,CFH[cfx_args][cfe]);
      Indent(indent);
      fprintf(FREPORT_TXT,"arg %s\n",(char *)rp->item);
      }

   fprintf(FREPORT_HTML,")");
   fprintf(FREPORT_TXT,"\n");
   }

Indent(indent);
fprintf(FREPORT_TXT,"{\n");

for (cp = body->conlist; cp != NULL; cp=cp->next)
   {
   fprintf(FREPORT_HTML,"%s.....%s%s => ",CFH[cfx_lval][cfb],cp->lval,CFH[cfx_lval][cfe]);
   Indent(indent);
   fprintf(FREPORT_TXT,"%s => ",cp->lval);

   fprintf(FREPORT_HTML,"\'%s",CFH[cfx_rval][cfb]);

   ShowRval(FREPORT_HTML,cp->rval,cp->type);
   ShowRval(FREPORT_TXT,cp->rval,cp->type);

   fprintf(FREPORT_HTML,"\'%s",CFH[cfx_rval][cfe]);

   if (cp->classes != NULL)
      {
      fprintf(FREPORT_HTML," if sub-body context %s%s%s\n",CFH[cfx_class][cfb],cp->classes,CFH[cfx_class][cfe]);
      fprintf(FREPORT_TXT," if sub-body context %s\n",cp->classes);
      }
   else
      {
      fprintf(FREPORT_TXT,"\n");
      }
   }

Indent(indent);
fprintf(FREPORT_TXT,"}\n");
}
