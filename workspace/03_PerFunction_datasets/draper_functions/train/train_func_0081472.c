task_parse_options(int cmd, char **arg, POptions po)
{
    while(*++arg) {
        switch(pit_arg_option(arg)) {
        case 'n':
            po->task.name = pit_arg_string(++arg, "task name");
            break;
        case 's':
            po->task.status = pit_arg_string(++arg, "task status");
            break;
        case 'p':
            if (cmd == 'm') {
                po->task.project_id = pit_arg_number(++arg, "project number");
            } else {
                po->task.priority = pit_arg_string(++arg, "task priority");
            }
            break;
        case 'd':
            po->task.date = pit_arg_date(++arg, "task date");
            break;
        case 'D':
            po->task.date_max = pit_arg_date(++arg, "task end date");
            break;
        case 't':
            po->task.time = pit_arg_time(++arg, "task time");
            break;
        case 'T':
            po->task.time_max = pit_arg_time(++arg, "task max time");
            break;
        default:
            die("invalid task option: %s", *arg);
        }
    }
}
