ProfilerSignalHandler(int signal, siginfo_t* info, void* context) {
#ifndef V8_HOST_ARCH_MIPS
  USE(info);
  if (signal != SIGPROF) return;
  if (active_sampler_ == NULL || !active_sampler_->IsActive()) return;
  if (vm_tid_ != GetThreadID()) return;

  TickSample sample_obj;
  TickSample* sample = CpuProfiler::TickSampleEvent();
  if (sample == NULL) sample = &sample_obj;


  ucontext_t* ucontext = reinterpret_cast<ucontext_t*>(context);
  mcontext_t& mcontext = ucontext->uc_mcontext;
  sample->state = Top::current_vm_state();
#if V8_HOST_ARCH_IA32
  sample->pc = reinterpret_cast<Address>(mcontext.gregs[REG_EIP]);
  sample->sp = reinterpret_cast<Address>(mcontext.gregs[REG_ESP]);
  sample->fp = reinterpret_cast<Address>(mcontext.gregs[REG_EBP]);
#elif V8_HOST_ARCH_X64
  sample->pc = reinterpret_cast<Address>(mcontext.gregs[REG_RIP]);
  sample->sp = reinterpret_cast<Address>(mcontext.gregs[REG_RSP]);
  sample->fp = reinterpret_cast<Address>(mcontext.gregs[REG_RBP]);
#elif V8_HOST_ARCH_ARM

#if (__GLIBC__ < 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ <= 3))
  sample->pc = reinterpret_cast<Address>(mcontext.gregs[R15]);
  sample->sp = reinterpret_cast<Address>(mcontext.gregs[R13]);
  sample->fp = reinterpret_cast<Address>(mcontext.gregs[R11]);
#else
  sample->pc = reinterpret_cast<Address>(mcontext.arm_pc);
  sample->sp = reinterpret_cast<Address>(mcontext.arm_sp);
  sample->fp = reinterpret_cast<Address>(mcontext.arm_fp);
#endif
#elif V8_HOST_ARCH_MIPS

  UNIMPLEMENTED();
#endif
  active_sampler_->SampleStack(sample);
  active_sampler_->Tick(sample);
#endif
}
