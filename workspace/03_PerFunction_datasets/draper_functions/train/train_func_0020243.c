main(int argc, char **argv)
{ if (argc > 1)
    factory = argv[1];
  std::cout << "Connecting to factory " << factory << std::endl;
  Adder adder;
  Counter counter1((char*)"myCounter");
  Counter counter2((char*)"myCounter");
  adder.set(2.0);
  counter1.set(adder.get());
  adder.add(3.0);
  counter1.inc();
  std::cout << "Adder=" << adder.get() << std::endl;
  std::cout << "Counter=" << counter2.get() << std::endl;
  std::cout << "Sleep for 90 seconds to test factory server purging objects:" << std::endl;

  sleep(30);
  counter1.inc();
  std::cout << "Counter=" << counter2.get() << std::endl;
  sleep(30);
  counter1.inc();
  std::cout << "Counter=" << counter2.get() << std::endl;
  sleep(30);
  counter1.inc();
  std::cout << "Counter=" << counter2.get() << std::endl;

  std::cout << "Adder is no longer available:" << std::endl;
  adder.add(3.0);
  std::cout << "Adder status = " << adder.status << std::endl;
  return 0;
}
