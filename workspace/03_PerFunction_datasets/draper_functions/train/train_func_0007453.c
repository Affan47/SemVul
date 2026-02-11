gtk_meter_set_adjustment (GtkMeter      *meter,
			  GtkAdjustment *adjustment)
{
  g_return_if_fail (meter != NULL);
  g_return_if_fail (GTK_IS_METER (meter));

  if (meter->adjustment)
    {
      gtk_signal_disconnect_by_data (GTK_OBJECT (meter->adjustment), (gpointer) meter);
      gtk_object_unref (GTK_OBJECT (meter->adjustment));
    }

  meter->adjustment = adjustment;
  gtk_object_ref (GTK_OBJECT (meter->adjustment));

  gtk_signal_connect (GTK_OBJECT (adjustment), "changed",
		      (GtkSignalFunc) gtk_meter_adjustment_changed,
		      (gpointer) meter);
  gtk_signal_connect (GTK_OBJECT (adjustment), "value_changed",
		      (GtkSignalFunc) gtk_meter_adjustment_value_changed,
		      (gpointer) meter);

  meter->old_value = adjustment->value;
  meter->old_lower = adjustment->lower;
  meter->old_upper = adjustment->upper;
  meter->iec_lower = iec_scale(adjustment->lower);
  meter->iec_upper = iec_scale(adjustment->upper);
  meter->amber_frac = (iec_scale(meter->amber_level) - meter->iec_lower) /
	            (meter->iec_upper - meter->iec_lower);

  gtk_meter_update (meter);
}
