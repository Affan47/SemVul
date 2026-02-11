xsh_background_poly(xsh_pre* pre, cpl_table** grid_tab,xsh_background_param* background_par) {


  polynomial* background = NULL;
  double mse = 0, rmse = 0;
  cpl_size total_clipped = 0;
  cpl_image* bkg_img = NULL;

  int degx = background_par->poly_deg_x;
  int degy = background_par->poly_deg_y;
  double kappa = background_par->poly_kappa;
  xsh_msg("degx=%d degy=%d kappa=%g", degx, degy, kappa);


  {
    cpl_size n_clipped;
    do {
      cpl_size deg_xy = (degx + 1) * (degy + 1);
      assure(
          cpl_table_get_nrow(*grid_tab) > (degx + 1)*(degy + 1),
          CPL_ERROR_ILLEGAL_OUTPUT,
          "Too few sample points available (%" CPL_SIZE_FORMAT " point(s)) to make the fit "
          "(more than %" CPL_SIZE_FORMAT " points needed). "
          "Increase number of sample points or increase kappa", cpl_table_get_nrow(*grid_tab), deg_xy);


      xsh_polynomial_delete(&background);
      check_msg(
          background = xsh_polynomial_regression_2d( *grid_tab, "X", "Y", "INT", "ERR", degx, degy, "INTfit", NULL, NULL, &mse, NULL, NULL, kappa, -1),
          "Error fitting polynomial");


      cpl_table_duplicate_column(*grid_tab, "Residual", *grid_tab, "INT");
      cpl_table_subtract_columns(*grid_tab, "Residual", "INTfit");


      rmse = cpl_table_get_column_stdev(*grid_tab, "Residual");

      xsh_msg_dbg_medium("rmse=%g", rmse);

      if (kappa > 0) {
        check_msg(
            n_clipped = xsh_select_table_rows( *grid_tab, "Residual", CPL_GREATER_THAN, kappa * rmse),
            "Error selecting rows");


      } else {
        n_clipped = 0;
      }

      total_clipped += n_clipped;


      xsh_msg(
           "RMS = %f. %" CPL_SIZE_FORMAT " of %" CPL_SIZE_FORMAT " points rejected in kappa-sigma clipping", rmse, n_clipped, cpl_table_get_nrow(*grid_tab));

      cpl_table_erase_selected(*grid_tab);

      if (n_clipped > 0) {
        cpl_table_erase_column(*grid_tab, "INTfit");
        cpl_table_erase_column(*grid_tab, "Residual");
      }

    } while (n_clipped > 0);
  }


  {
    double percentage = 100.0 * ((double) total_clipped)
        / (total_clipped + cpl_table_get_nrow(*grid_tab));

    if (kappa > 0) {
      xsh_msg_dbg_medium(
          "%" CPL_SIZE_FORMAT " of %" CPL_SIZE_FORMAT " points (%.2f %%) were rejected in "
          "kappa-sigma clipping. RMS = %.2f ADU", total_clipped, cpl_table_get_nrow(*grid_tab) + total_clipped, percentage, sqrt(mse));
    }


  }

  check_msg( bkg_img=xsh_image_generate_background(pre->nx,pre->ny, background),
      "Error generating background polynomial");

  cleanup:

  xsh_polynomial_delete(&background);
  return bkg_img;

}
