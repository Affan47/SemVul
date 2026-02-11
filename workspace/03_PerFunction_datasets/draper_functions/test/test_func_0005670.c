match(const ExecutionTarget& et) const {
    if(!BrokerPlugin::match(et)) return false;
    return et.Benchmarks->find(benchmark) != et.Benchmarks->end();
  }
}
