ShowHelpCommandLine(const char* strExec)
{
  CLockObject lock(g_outputMutex);
  cout << endl <<
      strExec << " {-h|--help|-l|--list-devices|[COM PORT]}" << endl <<
      endl <<
      "parameters:" << endl <<
      "  -h --help                   Shows this help text" << endl <<
      "  -l --list-devices           List all devices on this system" << endl <<
      "  -t --type {p|r|t|a}         The device type to use. More than one is possible." << endl <<
      "  -p --port {int}             The HDMI port to use as active source." << endl <<
      "  -b --base {int}             The logical address of the device to with this " << endl <<
      "                              adapter is connected." << endl <<
      "  -f --log-file {file}        Writes all libCEC log message to a file" << endl <<
      "  -r --rom                    Read persisted settings from the EEPROM" << endl <<
      "  -sf --short-log-file {file} Writes all libCEC log message without timestamps" << endl <<
      "                              and log levels to a file." << endl <<
      "  -d --log-level {level}      Sets the log level. See cectypes.h for values." << endl <<
      "  -s --single-command         Execute a single command and exit. Does not power" << endl <<
      "                              on devices on startup and power them off on exit." << endl <<
      "  -o --osd-name {osd name}    Use a custom osd name." << endl <<
      "  -m --monitor                Start a monitor-only client." << endl <<
      "  -i --info                   Shows information about how libCEC was compiled." << endl <<
      "  [COM PORT]                  The com port to connect to. If no COM" << endl <<
      "                              port is given, the client tries to connect to the" << endl <<
      "                              first device that is detected." << endl <<
      endl <<
      "Type 'h' or 'help' and press enter after starting the client to display all " << endl <<
      "available commands" << endl;
}
