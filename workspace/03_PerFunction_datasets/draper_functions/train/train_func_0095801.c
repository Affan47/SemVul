m_redo(GtkWidget *, cchar *)
{
   if (CEF) {
      edit_redo();
      return;
   }

   if (Pundo == Pumax) return;
   if (! menulock(1)) return;
   Pundo++;
   if (KB_A_key) Pundo = Pumax;
   load_undo();
   Fmodified = Pundo;
   menulock(0);
   return;
}
