updateParametersA(VectorArray<double> const& deltaAi)
   {
      Vector3d T, omega;
      Matrix3x3d R0, dR;

      for (int i = _nNonvaryingA; i < _nParametersA; ++i)
      {
         T = _cams[i].getTranslation();
         T[0] += deltaAi[i][0];
         T[1] += deltaAi[i][1];
         T[2] += deltaAi[i][2];
         _cams[i].setTranslation(T);


         R0 = _cams[i].getRotation();
         omega[0] = deltaAi[i][3];
         omega[1] = deltaAi[i][4];
         omega[2] = deltaAi[i][5];
         createRotationMatrixRodriguez(omega, dR);
         _cams[i].setRotation(dR * R0);
      }
   }
