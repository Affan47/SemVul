on_response(int v)
{
  if (v == 0)
    {

      std::vector<Joystick::CalibrationData> data;

      for(int i = 0; i < joystick.get_axis_count(); ++i)
        {
          Joystick::CalibrationData axis;
          axis.calibrate  = true;
          axis.invert     = false;
          axis.center_min = axis.center_max = joystick.get_axis_state(i);
          axis.range_min  = min_axis_state[i];
          axis.range_max  = max_axis_state[i];


          if (axis.center_min == axis.range_min ||
              axis.center_max == axis.range_max)
            {
              axis.center_min = axis.center_max = (axis.range_min + axis.range_max)/2;
            }

          data.push_back(axis);
        }

      joystick.set_calibration(data);

      hide();
    }
  else
    {
      joystick.set_calibration(orig_data);
    }
}
