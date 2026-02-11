SetTrialBoundMultipliersFromStep(Number alpha,
      const Vector& delta_z_L,
      const Vector& delta_z_U,
      const Vector& delta_v_L,
      const Vector& delta_v_U)
  {
    DBG_ASSERT(have_prototypes_);

    SmartPtr<IteratesVector> newvec = trial()->MakeNewContainer();
    newvec->create_new_z_L();
    newvec->z_L_NonConst()->AddTwoVectors(1., *curr()->z_L(), alpha, delta_z_L, 0.);

    newvec->create_new_z_U();
    newvec->z_U_NonConst()->AddTwoVectors(1., *curr()->z_U(), alpha, delta_z_U, 0.);

    newvec->create_new_v_L();
    newvec->v_L_NonConst()->AddTwoVectors(1., *curr()->v_L(), alpha, delta_v_L, 0.);

    newvec->create_new_v_U();
    newvec->v_U_NonConst()->AddTwoVectors(1., *curr()->v_U(), alpha, delta_v_U, 0.);

    set_trial(newvec);
  }
