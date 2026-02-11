CalibrateJoystick(TXT_UNCAST_ARG(widget), TXT_UNCAST_ARG(unused))
{
    calibrate_stage = CALIBRATE_CENTER;


    if (!OpenAllJoysticks())
    {
        NoJoystick();
        return;
    }

    calibration_window = TXT_NewWindow("Joystick calibration");

    TXT_AddWidgets(calibration_window,
                   TXT_NewLabel("Please follow the following instructions\n"
                                "in order to calibrate your joystick."),
                   TXT_NewStrut(0, 1),
                   calibration_label = TXT_NewLabel("zzz"),
                   TXT_NewStrut(0, 1),
                   NULL);

    TXT_SetWindowAction(calibration_window, TXT_HORIZ_LEFT, NULL);
    TXT_SetWindowAction(calibration_window, TXT_HORIZ_CENTER,
                        TXT_NewWindowAbortAction(calibration_window));
    TXT_SetWindowAction(calibration_window, TXT_HORIZ_RIGHT, NULL);

    TXT_SetWidgetAlign(calibration_label, TXT_HORIZ_CENTER);
    TXT_SDL_SetEventCallback(CalibrationEventCallback, NULL);

    TXT_SignalConnect(calibration_window, "closed", CalibrateWindowClosed, NULL);


    joystick_index = -1;
    calibrate_stage = CALIBRATE_CENTER;

    SetCalibrationLabel();
}
