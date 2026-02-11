main()
{
   const int test_case = 4;

#ifndef WIN32
   void* (*Test_Srv[test_case])(void*);
   void* (*Test_Cli[test_case])(void*);
#else
   DWORD (WINAPI *Test_Srv[test_case])(LPVOID);
   DWORD (WINAPI *Test_Cli[test_case])(LPVOID);
#endif

   Test_Srv[0] = Test_1_Srv;
   Test_Cli[0] = Test_1_Cli;
   Test_Srv[1] = Test_2_Srv;
   Test_Cli[1] = Test_2_Cli;
   Test_Srv[2] = Test_3_Srv;
   Test_Cli[2] = Test_3_Cli;
   Test_Srv[3] = Test_4_Srv;
   Test_Cli[3] = Test_4_Cli;

   for (int i = 0; i < test_case; ++ i)
   {
      cout << "Start Test # " << i + 1 << endl;

      UDT::startup();

#ifndef WIN32
      pthread_t srv, cli;
      pthread_create(&srv, NULL, Test_Srv[i], NULL);
      pthread_create(&cli, NULL, Test_Cli[i], NULL);

      pthread_join(srv, NULL);
      pthread_join(cli, NULL);
#else
      HANDLE srv, cli;
      srv = CreateThread(NULL, 0, Test_Srv[i], NULL, 0, NULL);
      cli = CreateThread(NULL, 0, Test_Cli[i], NULL, 0, NULL);

      WaitForSingleObject(srv, INFINITE);
      WaitForSingleObject(cli, INFINITE);
#endif

      UDT::cleanup();

      cout << "Test # " << i + 1 << " completed." << endl;
   }

   return 0;
}
