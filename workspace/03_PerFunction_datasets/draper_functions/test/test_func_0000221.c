_math_matrix_analyse( GLmatrix *mat )
{
   if (mat->flags & MAT_DIRTY_TYPE) {
      if (mat->flags & MAT_DIRTY_FLAGS)
	 analyse_from_scratch( mat );
      else
	 analyse_from_flags( mat );
   }

   if (mat->inv && (mat->flags & MAT_DIRTY_INVERSE)) {
      matrix_invert( mat );
      mat->flags &= ~MAT_DIRTY_INVERSE;
   }

   mat->flags &= ~(MAT_DIRTY_FLAGS | MAT_DIRTY_TYPE);
}
