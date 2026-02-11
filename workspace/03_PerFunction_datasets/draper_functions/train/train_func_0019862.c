calc_control_signal_rate_pid(int32_t motor_setpoint[], uint32_t nr_motors, control_values_pid_t *parameters_pid, control_values_pid_t *ctrl_error, state_data_t *state, state_data_t *setpoint, control_signal_t *ctrl_signal)
{

    static control_signal_t error_d_last = {};


    ctrl_error->pitch_p =  (setpoint->pitch_rate - state->pitch_rate);
    ctrl_error->pitch_i += (setpoint->pitch_rate - state->pitch_rate);
    ctrl_error->pitch_d = ((setpoint->pitch_rate - state->pitch_rate) - error_d_last.torque_pitch);
    ctrl_error->roll_p =  (setpoint->roll_rate - state->roll_rate);
    ctrl_error->roll_i += (setpoint->roll_rate - state->roll_rate);
    ctrl_error->roll_d = ((setpoint->roll_rate - state->roll_rate) - error_d_last.torque_roll);
    ctrl_error->yaw_p =  (setpoint->yaw_rate - state->yaw_rate);
    ctrl_error->yaw_i += (setpoint->yaw_rate - state->yaw_rate);
    ctrl_error->yaw_d = ((setpoint->yaw_rate - state->yaw_rate) - error_d_last.torque_yaw);


    error_d_last.torque_pitch = ctrl_error->pitch_p;
    error_d_last.torque_roll = ctrl_error->roll_p;
    error_d_last.torque_yaw = ctrl_error->yaw_p;


    ctrl_signal->torque_pitch = (my_mult(parameters_pid->pitch_p, ctrl_error->pitch_p) + my_mult(parameters_pid->pitch_i, ctrl_error->pitch_i) + my_mult(parameters_pid->pitch_d, ctrl_error->pitch_d)) >> SHIFT_EXP;
    ctrl_signal->torque_roll = (my_mult(parameters_pid->roll_p, ctrl_error->roll_p) + my_mult(parameters_pid->roll_i, ctrl_error->roll_i) + my_mult(parameters_pid->roll_d, ctrl_error->roll_d)) >> SHIFT_EXP;
    ctrl_signal->torque_yaw = (my_mult(parameters_pid->yaw_p, ctrl_error->yaw_p) + my_mult(parameters_pid->yaw_i, ctrl_error->yaw_i) + my_mult(parameters_pid->yaw_d, ctrl_error->yaw_d)) >> SHIFT_EXP;

    ctrl_signal->thrust = my_mult(parameters_pid->altitude_p, setpoint->z_vel);


    if (nr_motors == 4)
    {
        control_allocation_quad_x(ctrl_signal, motor_setpoint);
    }


}
