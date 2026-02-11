arth_arg(var, v_orig, chk, cnv)
struct il_code *var;
struct val_loc *v_orig;
int chk;
struct code *cnv;
   {
   struct code *lbl;
   struct code *cd;

   if (chk) {


      lbl = oper_lbl("converted");
      cd_add(lbl);
      cur_fnc->cursor = lbl->prev;
      if (cnv != NULL) {
         cd = NewCode(2);
         cd->cd_id = C_If;
         cd->Cond = cnv;
         cd->ThenStmt = mk_goto(lbl);
         cd_add(cd);
         }
      cd = alc_ary(3);
      cd->ElemTyp(0) = A_Str;
      cd->Str(0) =              "err_msg(102, &(";
      cd->ElemTyp(1) = A_ValLoc;
      cd->ValLoc(1) =           v_orig;
      cd->ElemTyp(2) = A_Str;
      cd->Str(2) =              "));";
      cd_add(cd);
      if (err_conv)
         cd_add(sig_cd(on_failure, cur_fnc));
      cur_fnc->cursor = lbl;
      }
   else if (cnv != NULL) {
      cd_add(cnv);
      cd = alc_ary(1);
      cd->ElemTyp(0) = A_Str;
      cd->Str(0) =              ";";
      cd_add(cd);
      }
   }
