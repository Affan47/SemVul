normalize_type(SwigType *ty) {
    SwigType *qty;
    if (CPlusPlus) {
      Replaceall(ty, "struct ", "");
      Replaceall(ty, "union ", "");
      Replaceall(ty, "class ", "");
    }

    qty = SwigType_typedef_qualified(ty);

    Clear(ty);
    Append(ty, qty);
    Delete(qty);
  }
