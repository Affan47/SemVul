UpdateInternalData(const Vector& s_new, const Vector& y_new,
                     SmartPtr<Vector> ypart_new)
  {
    DBG_START_METH("LimMemQuasiNewtonUpdater::UpdateInternalData",
                   dbg_verbosity);

    if (limited_memory_max_history_==0) {
      return false;
    }

    bool augment_memory;
    if (curr_lm_memory_ < limited_memory_max_history_) {
      augment_memory = true;
      curr_lm_memory_++;
    }
    else {
      augment_memory = false;
    }

    if (!update_for_resto_) {

      if (augment_memory) {


        AugmentMultiVector(S_, s_new);
        AugmentMultiVector(Y_, y_new);
        AugmentDenseVector(D_, s_new.Dot(y_new));
        AugmentLMatrix(L_, *S_, *Y_);
        DBG_ASSERT(SdotS_uptodate_ || S_->NCols()==1);
        AugmentSdotSMatrix(SdotS_, *S_);
        SdotS_uptodate_ = true;
      }
      else {

        ShiftMultiVector(S_, s_new);
        ShiftMultiVector(Y_, y_new);
        ShiftDenseVector(D_, s_new.Dot(y_new));
        ShiftLMatrix(L_, *S_, *Y_);
        DBG_ASSERT(SdotS_uptodate_);
        ShiftSdotSMatrix(SdotS_, *S_);
      }
    }
    else {

      if (limited_memory_special_for_resto_) {
        SmartPtr<Vector> DRs_new = s_new.MakeNewCopy();
        DRs_new->ElementWiseMultiply(*curr_red_DR_x_);
        if (augment_memory) {
          AugmentMultiVector(S_, s_new);
          AugmentMultiVector(DRS_, *DRs_new);
          AugmentMultiVector(Ypart_, *ypart_new);
          AugmentSTDRSMatrix(STDRS_, *S_, *DRS_);
        }
        else {
          ShiftMultiVector(S_, s_new);
          ShiftMultiVector(DRS_, *DRs_new);
          ShiftMultiVector(Ypart_, *ypart_new);
          ShiftSTDRSMatrix(STDRS_, *S_, *DRS_);
        }
      }
      else  {
        if (augment_memory) {
          AugmentMultiVector(S_, s_new);
          AugmentMultiVector(Ypart_, *ypart_new);
          DBG_ASSERT(SdotS_uptodate_ || S_->NCols()==1);
          AugmentSdotSMatrix(SdotS_, *S_);
          SdotS_uptodate_ = true;
        }
        else {
          ShiftMultiVector(S_, s_new);
          ShiftMultiVector(Ypart_, *ypart_new);
          DBG_ASSERT(SdotS_uptodate_);
          ShiftSdotSMatrix(SdotS_, *S_);
        }
      }
      DBG_PRINT((1,"curr_eta = %e\n", curr_eta_));
      DBG_PRINT_VECTOR(2,"curr_red_DR_x", *curr_red_DR_x_);
      DBG_PRINT_VECTOR(2,"S", *S_);
      DBG_PRINT_VECTOR(2,"Ypart", *Ypart_);
      RecalcY(curr_eta_, *curr_red_DR_x_, *S_, *Ypart_, Y_);
      DBG_PRINT_VECTOR(2,"Y", *Y_);
      RecalcD(*S_, *Y_, D_);
      RecalcL(*S_, *Y_, L_);
    }

    return augment_memory;
  }
